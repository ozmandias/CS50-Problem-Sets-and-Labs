import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        editid = request.form.get("id")
        if not editid:
            editid = -1
        birthdayexists = False
        # print(name+month+day)
        birthdays = db.execute("SELECT * FROM birthdays")
        # print(birthdays)
        #print(editid)
        for birthday in birthdays:
            if birthday["id"] == int(editid):
                birthdayexists = True
        if birthdayexists == False:
            db.execute("INSERT INTO birthdays(name,month,day) VALUES(?,?,?)",name,month,day)
        else:
            db.execute("UPDATE birthdays SET month=?, day=? WHERE id=?",month,day,editid)
            editid = -1
            birthdayexists = False
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html",birthdaysoffriends=birthdays)

@app.route("/edit")
def edit():
    idtoedit = request.args.get("id")
    friendtoedit = db.execute("SELECT * FROM birthdays WHERE id=?",idtoedit)
    # print(idtoedit)
    print(friendtoedit)
    # return "edit"
    return render_template("edit.html",friend=friendtoedit[0])

@app.route("/delete")
def delete():
    idtodelete = request.args.get("id")
    db.execute("DELETE FROM birthdays WHERE id=?",idtodelete)
    # print(idtodelete)
    return redirect("/")

