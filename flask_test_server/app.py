from flask import Flask, jsonify, json
app = Flask(__name__)

@app.route("/")
def home():
    return "Hello, Flask!"

@app.route("/sensorData")
def returnSensorData():
    data = jsonify(
        data=3
    )
    
    return data    