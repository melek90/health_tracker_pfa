let ctx = document.getElementById('chart').getContext('2d');

let dataPoints = [];

let chart = new Chart(ctx, {
    type: 'line',
    data: {
        labels: [],
        datasets: [{
            data: dataPoints,
            borderWidth: 2,
            tension: 0.2
        }]
    },
    options: {
        animation: false,
        responsive: false,
        plugins: { legend: { display: false } },
        scales: {
            x: { display: false },
            y: { min: 0, max: 255 }
        },
        elements: {
            point: { radius: 0 }
        }
    }
});


function update() {
  fetch('/get_data')
  .then(res => res.json())
  .then(data => {

    document.getElementById("bpm").innerText = data.bpm;
    document.getElementById("temp").innerText = data.temp;

    let newVal = data.ecg[data.ecg.length - 1];

    if (newVal !== undefined) {
      dataPoints.push(newVal);

      // limite taille (scroll ECG)
      if (dataPoints.length > 200) {
        dataPoints.shift();
      }

      chart.data.labels = dataPoints.map(() => '');
      chart.update();
    }
  });
}


setInterval(update, 30);