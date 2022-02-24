import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfoliostocks = db.execute("SELECT * FROM stocks JOIN users ON users.id=stocks.user_id WHERE user_id=?", session["user_id"])
    currentcash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    currentcash = currentcash[0]["cash"]
    grandtotal = 0
    buystatus = request.args.get("buy")
    salestatus = request.args.get("sale")
    changepasswordstatus = request.args.get("changepassword")
    # print(currentcash)
    if not portfoliostocks:
        return render_template("blank.html", cashmessage="10000")
    else:
        # print(portfoliostocks)
        for portfoliostock in portfoliostocks:
            updatestock = lookup(portfoliostock["symbol"])
            # print(updatestock)
            portfoliostock["price"] = updatestock["price"]
            portfoliostock["total"] = portfoliostock["price"] * portfoliostock["quantity"]
            db.execute("UPDATE stocks SET price=?,total=? WHERE id=? AND user_id=?",
                       portfoliostock["price"], portfoliostock["total"], portfoliostock["id"], session["user_id"])
            grandtotal = grandtotal + portfoliostock["total"]
        grandtotal = grandtotal + currentcash
        # print(portfoliostocks)
        return render_template("portfolio.html", portfoliotable=portfoliostocks, portfoliototal=grandtotal, buymessage=buystatus, salemessage=salestatus, useratsettings=False, changepasswordmessage=changepasswordstatus)
    # return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # return apology("TODO")
    if request.method == "POST":
        buysymbol = request.form.get("symbol")
        buysymbol = buysymbol.upper()
        sharequantity = request.form.get("shares")
        buyquote = lookup(buysymbol)
        usercash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        usercash = usercash[0]["cash"]

        if not buysymbol:
            return apology("missing symbol", 400)

        if sharequantity.isnumeric() == True:
            if not sharequantity or int(sharequantity) == 0:
                return apology("missing shares", 400)
            if int(sharequantity) < 1:
                return apology("invalid shares", 400)
        else:
            if sharequantity.isalpha() == True:
                return apology("invalid shares", 400)
            else:
                return apology("invalid shares", 400)

        if not buyquote:
            return apology("invalid symbol", 400)
        shareprice = buyquote["price"]

        # print("id:"+str(session["user_id"]))
        # print(db.execute("SELECT * FROM users WHERE id=?",session["user_id"]))
        # print(usercash[0]["cash"])
        # print(usercash)
        # print(buyquote)
        # print(shareprice)

        sharetotal = shareprice * int(sharequantity)
        if usercash < sharetotal:
            # return "not enough cash"
            return apology("can't afford")
        else:
            usercash = usercash - sharetotal
            checksymbol = db.execute("SELECT * FROM stocks WHERE symbol=? AND user_id=?", buysymbol, session["user_id"])
            # print(checksymbol)
            if not checksymbol:
                # print("not check symbol")
                db.execute("INSERT INTO stocks(user_id,symbol,name,quantity,price,total) VALUES(?,?,?,?,?,?)",
                           session["user_id"], buysymbol, buyquote["name"], sharequantity, shareprice, sharetotal)
            else:
                checksymbolid = checksymbol[0]["id"]
                currentchecksymbolquantity = checksymbol[0]["quantity"]
                currentchecksymboltotal = checksymbol[0]["total"]
                updatequantity = currentchecksymbolquantity + int(sharequantity)
                updateprice = shareprice
                updatetotal = updateprice * updatequantity
                db.execute("UPDATE stocks SET quantity=?, price=?, total=? WHERE id=?",
                           updatequantity, updateprice, updatetotal, checksymbolid)
            db.execute("UPDATE users SET cash=? WHERE id=?", usercash, session["user_id"])

        # return "bought"
        buydate = db.execute("SELECT DATE('now'), TIME('now')")
        buydate = ""+buydate[0]["DATE('now')"]+" "+buydate[0]["TIME('now')"]
        db.execute("INSERT INTO history(user_id,symbol,quantity,price,date) VALUES(?,?,?,?,?)",
                   session["user_id"], buysymbol, sharequantity, shareprice, buydate)
        return redirect("/?buy=success")
    else:
        return render_template("buy.html", useratsettings=False)


@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():
    # return "changepassword"
    currentuser = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])
    if request.method == "POST":
        originalhashpassword = currentuser[0]["hash"]
        oldpassword = request.form.get("oldpassword")
        newpassword = request.form.get("newpassword")
        newconfirmationpassword = request.form.get("newconfirmation")
        if not oldpassword:
            return apology("must provide old password", 400)
        if not newpassword:
            return apology("must provide new password", 400)
        if not newconfirmationpassword:
            return apology("must provide confirm password", 400)

        if check_password_hash(originalhashpassword, oldpassword) == True:
            if newpassword == newconfirmationpassword:
                newhashpassword = generate_password_hash(newpassword)
                db.execute("UPDATE users SET hash=? WHERE id=?", newhashpassword, session["user_id"])
            else:
                return apology("new password and confirm password do not match", 400)
        else:
            return apology("invalid old password", 400)
        return redirect("/?changepassword=success")
    else:
        return render_template("changepassword.html", usertochangepassword=currentuser, useratsettings=True)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # return apology("TODO")
    userhistory = db.execute("SELECT * FROM history WHERE user_id=?", session["user_id"])
    # print(userhistory)
    # return "history"
    return render_template("history.html", historytable=userhistory, useratsettings=False)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    registerstatus = request.args.get("register")

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html", registermessage=registerstatus)


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # return apology("TODO")
    stockquote = {}
    if request.method == "POST":
        stocksymbol = request.form.get("symbol")
        stocksymbol = stocksymbol.upper()
        # print(stocksymbol)
        if not stocksymbol:
            return apology("missing symbol", 400)
        stockquote = lookup(stocksymbol)
        if not stockquote:
            return apology("invalid symbol", 400)
        # print(stockquote)
        # return "quoted"
        return render_template("quoted.html", quotemessage=stockquote, useratsettings=False)
    else:
        return render_template("quote.html", useratsettings=False)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # return apology("TODO")
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmpassword = request.form.get("confirmation")
        # print("username:"+username+", "+"password:"+password+", "+"confirmpassword:"+confirmpassword)
        userexists = False
        users = db.execute("SELECT * FROM users")
        # print(users)

        if not username:
            return apology("must provide user name", 400)
        for user in users:
            if user["username"] == username:
                userexists = True
                break
            else:
                userexists = False
        if not password:
            return apology("must provide password", 400)
        if not password == confirmpassword:
            return apology("password and confirmpassword do not match", 400)
        hashpassword = generate_password_hash(password)
        # print("hashpassword:"+hashpassword)
        # return "registered"
        if userexists == False:
            db.execute("INSERT INTO users(username,hash) VALUES(?,?)", username, hashpassword)
        else:
            # return render_template("register.html", message="User Exists")
            return apology("User Exists", 400)
        return redirect("/login?register=success")
    else:
        return render_template("register.html", message="")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # return apology("TODO")
    availablesymbols = db.execute("SELECT symbol FROM stocks WHERE user_id=?", session["user_id"])
    availablesymbolposition = 0
    for availablesymbol in availablesymbols:
        availablesymbol = availablesymbol["symbol"]
        availablesymbols[availablesymbolposition] = availablesymbol
        availablesymbolposition = availablesymbolposition + 1
        # print(availablesymbol)
    # print(availablesymbols)

    if request.method == "POST":
        sellsymbol = request.form.get("symbol")
        sellquantity = request.form.get("shares")
        checkquantity = db.execute("SELECT quantity FROM stocks WHERE symbol=? AND user_id=?", sellsymbol, session["user_id"])
        checkquantity = checkquantity[0]["quantity"]
        originalcash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        originalcash = originalcash[0]["cash"]
        sellquote = lookup(sellsymbol)

        # print(checkquantity)
        if not sellsymbol:
            return apology("missing symbol", 400)
        if not sellquantity:
            return apology("missing shares", 400)
        if sellquantity.isnumeric() == True:
            if int(sellquantity) > int(checkquantity):
                return apology("too many shares", 400)
            if int(sellquantity) < 1:
                return apology("invalid shares", 400)
        else:
            if sellquantity.isalpha() == True:
                return apology("invalid shares", 400)
            else:
                return apology("invalid shares", 400)

        if not sellquote:
            return apology("invalid symbol", 400)
        sellprice = sellquote["price"]

        saletotal = sellprice * int(sellquantity)
        newquantity = int(checkquantity) - int(sellquantity)
        originalcash = originalcash + saletotal
        db.execute("UPDATE users SET cash=? WHERE id=?", originalcash, session["user_id"])
        if newquantity == 0:
            db.execute("DELETE FROM stocks WHERE symbol=? AND user_id=? AND quantity=?",
                       sellsymbol, session["user_id"], checkquantity)
        else:
            db.execute("UPDATE stocks SET quantity=? WHERE symbol=? AND user_id=?", newquantity, sellsymbol, session["user_id"])
        # return "Sold"
        saledate = db.execute("SELECT DATE('now'), TIME('now')")
        saledate = ""+saledate[0]["DATE('now')"]+" "+saledate[0]["TIME('now')"]
        sellquantitytext = "-"+sellquantity
        # print(saledate)
        db.execute("INSERT INTO history(user_id,symbol,quantity,price,date) VALUES(?,?,?,?,?)",
                   session["user_id"], sellsymbol, sellquantitytext, sellprice, saledate)
        return redirect("/?sale=success")
    else:
        return render_template("sell.html", availablesellsymbols=availablesymbols, useratsettings=False)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
