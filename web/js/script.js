/**
 * Function: fetchScores and debug
 * Author: Jurriaan Egmond
 * Date: 2025-04-10
 * Description: Fetches score data from the API and updates the score table in the frontend. and sends
 * a request to ESP to debug
 */
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
  fetch('https://192.168.178.56/debug', { method: 'GET' })
    .then(response => response.text())
    .then(data => console.log('ESP32 Response:', data))
    .catch(error => console.error('Error sending request:', error));
}

// when page is loaded, call the function
document.addEventListener('DOMContentLoaded', () => {
  fetchScores();
  document.getElementById('sendRequestBtn').addEventListener('click', sendRequestToESP32);
});