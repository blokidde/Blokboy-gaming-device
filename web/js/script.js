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

  // when page is loaded, call the function
  document.addEventListener('DOMContentLoaded', fetchScores);