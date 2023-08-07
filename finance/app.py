import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
@login_required
def index():
    """Show portfolio of stocks"""
    qlookup,ovr_price ={},{}
    stock_eq=0
    portfolio=db.execute("select stock_id, sum(shares) from history group by user_id,stock_id having user_id=?",session["user_id"])
    for stock in portfolio:
        qlookup[stock['stock_id']] = (lookup(stock["stock_id"]))
        ovr_price[stock['stock_id']] = round(qlookup[stock['stock_id']]['price'] * stock['sum(shares)'],2)
        stock_eq += ovr_price[stock['stock_id']]
    cash_eq = (db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"]))[0]["cash"]
    ovr_eq = stock_eq+cash_eq

    return render_template ("index.html",portfolio=portfolio,qlookup=qlookup,ovr_price=ovr_price,cash_eq=round(cash_eq,2),ovr_eq=round(ovr_eq,2))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        qlookup = lookup(request.form.get("symbol"))
        try:
            shares = int(request.form.get ("shares"))
        except:
            return apology("Enter a valid symbol and number of shares", 400)
        if not qlookup or shares <1:
            return apology("Enter a valid symbol and number of shares", 400)

        #Calculate if user can afford the purchase
        rows = db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"])
        balance = rows[0]["cash"] - (qlookup["price"] * shares)
        if balance < 0:
            return apology("Insufficient Funds", 400)

        #Update history table
        db.execute("insert into history (user_id,stock_id,shares,unit_price,ttl_price,tstamp) values(?,?,?,?,?,?)",session["user_id"],qlookup["symbol"],shares,qlookup["price"],shares*qlookup["price"],datetime.datetime.now())
        #update users balance
        db.execute("update users set cash = ? where id = ?",balance, session["user_id"])

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("buy.html")

@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    if request.method == "POST":
        add = int(request.form.get ("add"))
        if not add or add <1:
            return apology("Enter a valid amount of money", 403)

        #Calculate if user can afford the purchase
        balance = db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"])
        #update users balance
        db.execute("update users set cash = ? where id = ?",float(balance[0]["cash"]+add), session["user_id"])

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("add.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT stock_id,unit_price,shares,tstamp,tran FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html",history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

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
        return render_template("login.html")


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
    if request.method == "POST":
        quote = request.form.get ("symbol")
        if lookup(quote)==None:
            return apology("Enter a valid symbol", 400)
        else:
            return render_template("quoted.html",qlookup = lookup(quote))


    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # return apology("TODO")
    if request.method == "POST":
        username = request.form.get ("username")
        password = request.form.get ("password")
        confirmation = request.form.get ("confirmation")

        # Ensure username was submitted and unique; and password was submitted
        if not username or not password or password !=confirmation:
            return apology("must provide valid username and password", 400)

        else:
            person_rows = db.execute("SELECT * FROM users WHERE username = ?", username)
            if len(person_rows) >0:
                return apology("username exists already!", 400)

        # Insert user into db
        db.execute("insert into users (username,hash) values(?,?)",username,generate_password_hash(password))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        stock = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Please enter a Valid stock", 400)
        if not stock or shares<1:
            return apology("Please enter a Valid stock", 400)

        portfolio=db.execute("select stock_id, sum(shares) from history where stock_id = ? and user_id=?",stock,session["user_id"])
        if (portfolio[0]['sum(shares)'])<1:
            return apology("Please enter a stock you own", 400)
        elif not shares or shares>portfolio[0]['sum(shares)']:
            return apology("Please enter a valid number", 400)

        # Conduct stock for money transaction
        # stock = rows[0]["cash"] - (qlookup["price"] * shares)
        qlookup = lookup(stock)
        nbalance = round(qlookup['price']*shares + (db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"]))[0]["cash"],2)
        #update users balance
        db.execute("update users set cash = ? where id = ?",nbalance, session["user_id"])
        #add sell transaction as a negative number to reflect sold unit
        db.execute("insert into history (user_id,stock_id,shares,unit_price,ttl_price,tstamp,tran) values(?,?,?,?,?,?,?)",session["user_id"],stock,-abs(shares),qlookup["price"],-abs(shares*qlookup["price"]),datetime.datetime.now(),"sell")

        # Redirect user to home page
        return redirect("/")

    else:
        portfolio=db.execute("select stock_id, sum(shares) from history group by user_id,stock_id having user_id=?",session["user_id"])
        return render_template("sell.html",portfolio=portfolio)
