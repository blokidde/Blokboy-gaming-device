/*
 * This JavaScript-file checks every 10 seconds if there is a address available from the localhost run-tunnel.
 * If so; it puts the address in HTTP and HTTPS format on the website.
 * 
 * Author: Mats Otten
 * Date: 31 july 2022
 */

var getLocalhostRunAddress = function() {
    fetch('/dashboard/tunnel.php')
        .then((response) => response.json())
        .then((data) => {
            // Remove existing menu items in the footer navigation bar.
            var addressItems = document.querySelectorAll("#footer-nav .localhost-item");
            addressItems.forEach(item => item.remove());
            
            if(data.success) {
                var ul = document.querySelector("#footer-nav");
                
                // Create the menu item for HTTP
                var liHttp = document.createElement("li");
                liHttp.innerHTML = "<a href='http://" + data.address + "' class='mr-4 hover:underline md:mr-6 localhost-item'>HTTP tunnel</a>";
                ul.appendChild(liHttp);  
                
                // Create the menu item for HTTPS
                var liHttps = document.createElement("li");
                liHttps.innerHTML = "<a href='https://" + data.address + "' class='mr-4 hover:underline md:mr-6 localhost-item'>HTTPs tunnel</a>";
                ul.appendChild(liHttps);               
            }
        });
};

window.addEventListener('load', function() {
    // Get address on page load
    getLocalhostRunAddress();
    // Get address every 10 seconds.
    setInterval(getLocalhostRunAddress, 10000);
});