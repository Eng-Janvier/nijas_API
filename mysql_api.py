from flask import *
import mysql.connector as mysql
App = Flask(__name__)
App.config['DEBUG'] = True

# db = mysql.connect(
#     host = "localhost",
#     user = "root",
#     passwd = "",
#     database = "flask_api"
# )
# cursor = db.cursor()

@App.route('/insert/dht/data', methods = ['GET'])
def api_data():
    global temp
    global hum
    if 'Temperature' in request.args and 'Humidity' in request.args:
        temp = float(request.args['Temperature'])
        hum = float(request.args['Humidity'])
        querry = "INSERT INTO dht_api (TEMPERATURE,HUMIDITY) VALUES (%s,%s)"
        values =(temp,hum)
        # cursor.execute(querry,values)
        # db.commit()
        return "Hello World, This Nijas"
    else:
        return "<h1> No data entries provided,</h1><p> Please provide a list of data to be inserted.</p>"

    return "<h1> Welcome to MySql Data Record System,</h1> <p> Your data has been recorded successfully.</p>"

@App.route('/sensor/dashboard')
def dashboard():
    return render_template('Dashboard.html',temp=temp,hum=hum)




if __name__ == '__main__':
    App.run(debug = True,host = '0.0.0.0')
    
