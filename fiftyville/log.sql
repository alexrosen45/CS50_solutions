-- Keep a log of any SQL queries you execute as you solve the mystery.
-- find number of people to be investigated
SELECT COUNT(name) FROM people;
-- get crime reports with keyword Duck
SELECT description FROM crime_scene_reports WHERE description LIKE "%Duck%";
-- ensure that reports are from correct street
SELECT description FROM crime_scene_reports WHERE description LIKE "%Duck%" AND street = "Humphrey Street";
-- get interviews that mentions the bakery
SELECT name, transcript FROM interviews WHERE transcript LIKE "%bakery%" OR transcript LIKE "%Bakery%";
-- get year of duck theft
SELECT year FROM crime_scene_reports WHERE description LIKE "%Duck%";
-- get interviews that mentions the bakery with matching year
SELECT name, transcript FROM interviews WHERE transcript LIKE "%bakery%" OR transcript LIKE "%Bakery%" AND year = 2021;
-- get security logs from parking lot
SELECT activity, license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28;
-- get call logs from bakery with a duration of 30
SELECT caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration = 30;
-- get call logs from bakery with a duration similar to 30
SELECT caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration > 20 AND duration < 40;
-- get call logs from bakery with a duration less than 1
SELECT caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 1;
-- get interviews that mentions the bakery with matching date
SELECT name, transcript FROM interviews WHERE transcript LIKE "%bakery%" OR transcript LIKE "%Bakery%" AND year = 2021 AND month = 7 AND day = 28;


-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- get withdrawals from that day

-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- get time of theft
SELECT description FROM crime_scene_reports WHERE description LIKE "%Duck%";
-- took place at 10 hours 15 minutes, so check for cars that left the parking lot inbetween 10:05 and 10:25
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 5 AND minute < 25 AND activity = "exit";
-- assign name
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 5 AND minute < 25 AND activity = "exit");
-- match with calls lasting longer than a minute for receiver (no matches for receiver)
SELECT name, phone_number FROM people WHERE phone_number IN (
    SELECT caller FROM phone_calls WHERE caller IN (
        SELECT phone_number FROM people WHERE license_plate IN (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 5 AND minute < 25 AND activity = "exit"
        )
    )
    AND year = 2021 AND month = 7 AND day = 28 AND duration < 60
);

-- check for money withdrawal
SELECT name FROM people WHERE id IN (
    SELECT person_id FROM bank_accounts WHERE account_number In (
        SELECT account_number FROM atm_transactions WHERE account_number IN (
            SELECT account_number FROM bank_accounts WHERE person_id IN (
                SELECT id FROM people WHERE phone_number IN (
                    SELECT caller FROM phone_calls WHERE caller IN (
                        SELECT phone_number FROM people WHERE license_plate IN (
                            SELECT license_plate FROM bakery_security_logs
                            WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 5 AND minute < 25 AND activity = "exit"
                        )
                    )
                    AND year = 2021 AND month = 7 AND day = 28 AND duration < 60
                )
            )
        )
        AND year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
    )
);

-- diana or bruce
-- get earliest flights by hour
SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour DESC;
-- get earliest flights by minute
SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8 ORDER BY minute DESC;

-- get passengers on earliest flight
SELECT name FROM people WHERE passport_number IN (
    SELECT passport_number FROM passengers WHERE flight_id IN (
        SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8 ORDER BY minute DESC
    )
);

-- therefore Bruce is the theif

-- find his accomplice who was on the other end of the phone
SELECT name FROM people WHERE phone_number IN (
    SELECT receiver FROM phone_calls WHERE caller IN (
        SELECT phone_number FROM people WHERE name = "Bruce"
    )
    AND year = 2021 AND month = 7 AND day = 28 AND duration < 60
);

-- therefore accomplice is robin

-- get destination
SELECT city FROM airports WHERE id IN (
    SELECT destination_airport_id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8 ORDER BY minute DESC
);

-- Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- check calls from Eugene corroborated list wtih possible callers and recievers (two queries)



-- Kiana | I saw Richard take a bite out of his pastry at the bakery before his pastry was stolen from him.



-- Emma | I'm the bakery owner, and someone came in, suspiciously whispering into a phone for about half an hour. They never bought anything.