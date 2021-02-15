from flask import Flask, jsonify, json
from random import uniform, randint, getrandbits
app = Flask(__name__)

@app.route("/")
def home():
    return "Hello, Flask!"

@app.route("/sensorData")
def returnSensorData():
    data = jsonify(
        Temperature=uniform(20.0, 30.0),
        Air_humidity=randint(0, 100),
        Soil_Moisture=randint(0, 100),
        Weather="Sunny",
        MCU_Device_ID="random_secret_id",
        DEVICE_ID="device_random_secret_id",
        Mode="Manual",
        Auto_Mode_Type="Summer",
        Heat=randint(0, 100),
        Light=randint(0, 100),
        Wind=bool(getrandbits(1)),
        Rain=bool(getrandbits(1))
    )
    
    return data    