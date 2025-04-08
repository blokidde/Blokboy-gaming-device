# how can i make the connection between client and server safer?

### subquestions/parts
- [Introduction](#Introduction)
- [What are the differences http and https](#What-are-the-differences-http-and-https)
- [How does https improve the safety?](#How-does-https-improve-the-safety)
- [What do i need to upgrade http to https?](#What-do-i-need-to-upgrade-http-to-https)
- [How do i test the upgraded safety?](#How-do-i-test-the-upgraded-safety)
- [Why is security important?](#Why-is-security-important)
- [Are there issues that arise from switching to https?](#Are-there-issues-that-arise-from-switching-to-https)
- [Sources](#Sources)

## Introduction
HTTP stands for hypertext transfer protocol. It is used to send information over the internet between a client and a server. However HTTP is not secure, this means anyone can see the message sent. This is ofcourse sub optimal for safety reasons.
https://www.cloudflare.com/learning/ddos/glossary/hypertext-transfer-protocol-http/

HTTPS stands for hypertext transfer protocol secure. It is the upgraded version of HTTP, it uses something called TLS, which stands for transport layer security. This is an encryption program, it encrypts the message sent between client and server.This encryption makes sure that outsiders cannot read or change the data, even if/when they manage to intercept it.
https://www.ssl.com/faqs/what-is-https/

By upgrading HTTP to HTTPS, a layer of security is added. When someone tries to look at the message sent from client to server through a program like wireshark they can see the entire HTTP message plain as day. With HTTPS you could only see an encrypted message.

For developers working on web-based applications, projects using web servers or any other IOT projects, security is essential. Whether you're building a scoreboard system, a login form, or controlling hardware remotely, upgrading from HTTP to HTTPS adds a necessary layer of protection.

This upgrade improves not only the security of the system, but also trustworthiness, if others will interact with or use the application. It shows the developer cares about data privacy and modern web standards.

## What are the differences http and https

| Feature             | HTTP                                             | HTTPS                                                  |
|---------------------|--------------------------------------------------|--------------------------------------------------------|
| Full Name           | HyperText Transfer Protocol                      | HyperText Transfer Protocol Secure                     |
| Security            | Not secure (data is sent as normal text)         | Secure (data is encrypted)                             |
| Data Protection     | Anyone on the network can read or modify the data| Only the sender and receiver can read the data         |
| Port                | Uses port 80 by default                          | Uses port 443 by default                               |
| URL Prefix          | http://                                          | https://                                               |
| SSL/TLS Certificate | Not required                                     | Required for encryption and identity verification      |
| Browser Lock Icon   | No lock icon, or shows "Not secure"              | Shows a lock icon in the address bar                   |
| Performance         | Slightly faster, but vulnerable                  | Slightly slower due to encryption, but safe            |
| SEO & Trust         | Lower SEO ranking; users may be warned           | Better SEO ranking; users trust it more                |

## how does https improve the safety?
HTTPS improves the safety of communication between a client and a server in three important ways: encryption, authentication, and data integrity. This protection is made possible by using TLS (Transport Layer Security), a protocol that ensures data is transferred securely over the internet.

### Encryption
ensures that the data sent from the client to the server is scrambled into unreadable characters. When using HTTP, this data is sent as plain text, meaning anyone on the same network — for example, using a program like Wireshark — can easily read it. This is dangerous when sending sensitive information like usernames, scores, or commands to a device. With HTTPS, the data is encrypted, so even if someone intercepts it, they will only see unreadable characters. This keeps the content of the communication private and secure.

### Authentication

### Data integrity

## What do i need to upgrade http to https?
to upgrade you need at least these things:
- tls(ssl) certificate
- https capable server
- updated URL's

## How do i test the upgraded safety?
### HTTP
![http_wireshark](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/http_wireshark.png)
here we see a wireshark screenshot with a few important parts. this is a http message that was sent from the ESP32(server) to the API. on the right bottom side we see the exact json message that was sent through http:

![http_json](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/http_json_mess.png)

on the left bottom side are a few pieces of information about the message like the length, amount of bytes and bits and the protocols used:

![http_message_info](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/http_message_info.png)

on the top you can see several different http messages, all of these were sent between server and client and the content can be easily read:

![http_top](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/http_messages.png)

## Why is security important?

## Are there issues that arise from switching to https?

### Sources
https://www.cloudflare.com/learning/ddos/glossary/hypertext-transfer-protocol-http/
https://www.ssl.com/faqs/what-is-https/