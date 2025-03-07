// this function gets the scores and playerID's from 
function fetchScores() {
  fetch('api/get.php')
    .then(response => response.json())
    .then(data => {
      const tbody = document.querySelector('#scoreTable tbody');
      tbody.innerHTML = '';

      data.forEach(item => {
        const tr = document.createElement('tr');

        // Player ID
        const tdPlayer = document.createElement('td');
        tdPlayer.textContent = item.player_id;
        tr.appendChild(tdPlayer);

        // Score
        const tdScore = document.createElement('td');
        tdScore.textContent = item.score_value;
        tr.appendChild(tdScore);

        tbody.appendChild(tr);
      });
    })
    .catch(error => {
      console.error('Error fetching scores:', error);
    });
}

function sendRequestToESP32() {
  fetch('http://192.168.178.56/command', { method: 'GET' })
    .then(response => response.text())
    .then(data => console.log('ESP32 Response:', data))
    .catch(error => console.error('Error sending request:', error));
}

// when page is loaded, call the function
document.addEventListener('DOMContentLoaded', fetchScores);