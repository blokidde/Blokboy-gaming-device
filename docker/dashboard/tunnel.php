<?php
/*
 * This PHP-file proxies between the localtunnel docker container and your website.
 * It will try to read the address of the localtunnel host from the log file
 * 
 * Author: Mats Otten
 * Date: 28 februari 2023
 */

header('Content-Type: application/json; charset=utf-8');

// Tries to fetch the contents of the log file from the server, if something goes wrong we going to ignore this.
$logFileContents = @file_get_contents("http://tunnel:8000/localtunnel");

// The log-file can contains the URL (if connected), starting with https and ending in loca.lt.
preg_match_all("/https:\/\/(.*?\.loca.lt)/", $logFileContents, $forwardMatches);

// If the URL is available; return this in JSON-format.
if(count($forwardMatches[0]) > 0) {
    die(json_encode(['success' => true, 'address' => $forwardMatches[1][0]]));
}

die(json_encode(['success' => false, 'message' => 'Cannot find localtunnel log-file.']));
?>