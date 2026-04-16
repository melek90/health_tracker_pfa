from flask import Flask, request, jsonify, render_template

app = Flask(__name__)


ecg_data = []
MAX_POINTS = 200

data = {
    "ecg": [],
    "bpm": 0,
    "spo2": 0,
    "temp": 0
}


@app.route('/')
def index():
    return render_template("index.html")


@app.route('/data')
def receive_data():
    global ecg_data, data

    ecg = request.args.get('ecg', type=int)
    bpm = request.args.get('bpm', type=float)
    spo2 = request.args.get('spo2', type=float)
    temp = request.args.get('temp', type=float)

    
    if ecg is not None:
        ecg_data.append(ecg)
        if len(ecg_data) > MAX_POINTS:
            ecg_data.pop(0)

    data["ecg"] = ecg_data
    data["bpm"] = int(bpm) if bpm else 0
    data["spo2"] = int(spo2) if spo2 else 0
    data["temp"] = round(temp, 1) if temp else 0

    return "OK"


@app.route('/get_data')
def get_data():
    return jsonify(data)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)