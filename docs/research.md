# how can i make the connection between client and server safer?

### subquestions/parts
- [Introduction](#Introduction)
- [What are the differences http and https](#What-are-the-differences-http-and-https)
- [How does https improve the safety?](#How-does-https-improve-the-safety)
- [What do i need to upgrade http to https?](#What-do-i-need-to-upgrade-http-to-https)
- [How do i test the upgraded safety?](#How-do-i-test-the-upgraded-safety)
- [Why is security important?](#Why-is-security-important)
- [Are there issues that arise from switching to https?](#Are-there-issues-that-arise-from-switching-to-https)
- [Research method](#Research-method)
- [Conclusion](#Conclusion)
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
https://chatgpt.com/

## how does https improve the safety?
HTTPS improves the safety of communication between a client and a server in three important ways: encryption, authentication, and data integrity. This protection is made possible by using TLS (Transport Layer Security), a protocol that ensures data is transferred securely over the internet.

### Encryption
ensures that the data sent from the client to the server is scrambled into unreadable characters. When using HTTP, this data is sent as plain text, meaning anyone on the same network — for example, using a program like Wireshark — can easily read it. This is dangerous when sending sensitive information like usernames, scores, or commands to a device. With HTTPS, the data is encrypted, so even if someone intercepts it, they will only see unreadable characters. This keeps the content of the communication private and secure.

### Authentication
Authentication ensures that the client communicates with the intended server, preventing attacks such as man-in-the-middle attack. HTTPS uses SSL/TLS certificates issued by trusted third-party authorities to verify the identity of servers. When connecting, the server presents its certificate, allowing the client to verify that the server is authentic and trusted.

### Data integrity
Data integrity ensures that messages exchanged between client and server cannot be altered during transmission. HTTPS, via TLS, includes integrity checks that detect any attempts to modify data packets while being sent. If data manipulation is detected, the connection is terminated, protecting the transmitted information from being changed by unauthorized people.

## What do i need to upgrade HTTP to HTTPS?
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

### HTTPS

This is a Wireshark capture using HTTPS. The content is encrypted, showing only "Encrypted Application Data":

![https_top](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/top_HTTPS.png)

Encrypted HTTPS message, showing no readable info(the higlighted part is the encrypted message):

![https_message_encoded](https://teemiixuujuu34-fa53a7.dev.hihva.nl/assets/message_HTTPS.png)

This shows the extra safety with HTTPS.

## Why is security important?
Security is important because the internet can be a dangerous place. Without good security, people with bad intentions can easily access your personal information or interfere with your systems. They might steal data, such as passwords or bank information, change your data, or even completely disrupt how your system works. This can lead to serious issues like identity theft, loss of money, damage to your reputation, or a loss of trust from your users.

A common attack is a man-in-the-middle attack (MITM). In a MITM attack, an attacker secretly sits between two people (or a device and a server) communicating over the internet. The attacker can read, copy, or even change the information being exchanged, all without either side noticing. To prevent MITM attacks, developers use encryption (like HTTPS) and certificates that ensure both sides are who they say they are.
https://www.cloudflare.com/learning/security/threats/man-in-the-middle-attack/

Another type of attack is called SQL injection. This happens when attackers use insecure input fields (like forms on websites) to send harmful instructions directly to a database. If these fields aren’t properly secured, attackers could access private data, delete or modify important information, or even take control of entire database. Preventing SQL injection involves carefully checking user input and using secure programming techniques to avoid letting attackers send illegal instructions.
https://portswigger.net/web-security/sql-injection

## Are there issues that arise from switching to https?
Switching from HTTP to HTTPS can give a few small problems like:
- setup is more difficult
- slower performance
- certificate renewal
https://chatgpt.com/

## Research method

To answer the research question, I looked at how HTTP and HTTPS work using both online sources and my own testing. I first tested an HTTP connection between my ESP32 and a local server, then captured the traffic using Wireshark. I repeated the test after upgrading to HTTPS and compared the results. This showed exactly what part of the message is visible and how that changes when encryption is used.

Next to testing, I also read multiple sources like Cloudflare, SSL.com, and OWASP to understand how encryption works, what kind of attacks HTTPS protects against, and how HTTPS is implemented in web applications and IoT projects.


## Conclusion

The main question was: How can I make the connection between client and server safer?

After comparing HTTP and HTTPS, reading about encryption methods, and testing it with Wireshark, I can say that HTTPS is the best option to make the connection safer. It protects the data in three ways: encryption, authentication, and data integrity. These make it much harder for attackers to read or change the data during transport.

I also found out what is needed to set up HTTPS: a TLS certificate, an HTTPS-capable server, and updated URLs in the client code. Testing with Wireshark clearly showed that with HTTP, the whole message is visible, but with HTTPS, the data is fully encrypted and unreadable for others on the network.

Some small downsides exist, like more setup time and performance cost, but the safety it adds is much more important. Security is especially needed in IOT or web projects where data is sent over the internet.


### Sources
- https://www.cloudflare.com/learning/ddos/glossary/hypertext-transfer-protocol-http/
- https://www.ssl.com/faqs/what-is-https/
- https://chatgpt.com/
- https://owasp.org/www-project-top-ten/
- https://www.cloudflare.com/learning/security/threats/man-in-the-middle-attack/
- https://portswigger.net/web-security/sql-injection