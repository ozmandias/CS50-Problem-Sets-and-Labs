-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema

.tables

.schema crime_scene_reports

-- Checks crime_scene_reports for clues.
SELECT * FROM crime_scene_reports;

.tables

.schema interviews

-- Checks interviews to learn that the thief drove away from the parking lot of the courthouse, withdrew some money from
SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2020;

.tables

.schema courthouse_security_logs

SELECT * FROM courthouse_security_logs WHERE day = 28 AND month = 7 AND year = 2020;

.tables

.schema atm_transactions

SELECT * FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7 AND year = 2020;

.tables

.schema bank_accounts

.schema people

SELECT name, account_number, license_plate, phone_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE account_number IN (28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199);

.tables

.schema phone_calls

SELECT * FROM phone_calls WHERE duration<60 AND day = 28 AND month = 7 AND year = 2020;

--Check Russell and the person that Russell called.
SELECT * FROM people WHERE phone_number = "(725) 555-3243";

SELECT * FROM people WHERE license_plate = "322W7JE";

.tables

.schema airports

.schema flights

SELECT * FROM airports;

SELECT * FROM flights WHERE day = 29 AND month = 7 AND year = 2020 ORDER BY hour;

.tables

.schema passengers

--Check the flight the Russell was in.
SELECT * FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2020);

SELECT name, passport_number FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id IN(SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2020)) ORDER BY name;

SELECT * FROM flights WHERE id = (SELECT flight_id FROM passengers WHERE passport_number = "3592750733");

SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = (SELECT flight_id FROM passengers WHERE passport_number = "3592750733"));

.tables

.schema people

SELECT name, account_number, license_plate, phone_number, passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE license_plate IN("5P2BI95", "94KL13X", "6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W&JE", "ONTHK55") OR account_number IN (28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199);

.tables

.schema phone_calls

SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE duration<60 AND day = 28 AND month = 7 AND year = 2020);

SELECT receiver, duration FROM phone_calls WHERE caller = "(367) 555-5533" AND duration<60 AND day = 28 AND month = 7 AND year = 2020;

SELECT * FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller = "(367) 555-5533" AND duration<60 AND day = 28 AND month = 7 AND year = 2020);

.tables

.schema airports

.schema flights

SELECT name, license_plate, phone_number, passport_number FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id IN(SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2020 AND hour = 8 AND minute = 20));

SELECT city FROM airports WHERE id = (SELECT destination_ariport_id FROM flights WHERE id = (SELECT flight_id FROM passengers WHERE passport_number = "5773159633"));

