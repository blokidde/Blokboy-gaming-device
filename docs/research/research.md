# how can i make the connection between client and server safer?

### subquestions/parts
- [introduction](#introduction)
- [what are the differences http and https](#what-are-the-differences-http-and-https)
- [how does https improve the safety?](#how-does-https-improve-the-safety)
- [what do i need to upgrade http to https?](#what-do-i-need-to-upgrade-http-to-https)
- [how do i test the upgraded safety?](#how-do-i-test-the-upgraded-safety)
- [why is security important?](#why-is-security-important)
- [are there issues that arise from switching to https?](#are-there-issues-that-arise-from-switching-to-https)
- [sources](#sources)

## introduction
HTTP stands for hypertext transfer protocol. It is used to send information over the internet between a client and a server. However HTTP is not secure, this means anyone can see the message sent. This is ofcourse sub optimal for safety reasons. 

HTTPS stands for hypertext transfer protocol secure. It is the upgraded version of HTTP, it uses something called TLS, which stands for transport layer security. This is an encryption program, it encrypts the message sent between client and server.This encryption makes sure that outsiders cannot read or tamper with the data, even if/when they manage to intercept it.

By upgrading HTTP to HTTPS, a layer of security is added. When someone tries to look at the message sent from client to server through a program like wireshark they can see the entire HTTP message plain as day. With HTTPS you could only see an encrypted message.

For developers working on web-based applications, projects using web servers or any other IOT projects, security is essential. Whether you're building a scoreboard system, a login form, or controlling hardware remotely, upgrading from HTTP to HTTPS adds a necessary layer of protection.

This upgrade improves not only the security of the system, but also trustworthiness, if others will interact with or use the application. It shows the developer cares about data privacy and modern web standards.

## what are the differences http and https

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
## what do i need to upgrade http to https?
to upgrade you need at least these things:
- ssl/tls certificate
- https capable server
- updated URL's
## how do i test the upgraded safety?
![frontpanel design](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/http_wireshark.png)
## why is security important?
## are there issues that arise from switching to https?


### sources
https://www.cloudflare.com/learning/ddos/glossary/hypertext-transfer-protocol-http/
https://www.ssl.com/faqs/what-is-https/