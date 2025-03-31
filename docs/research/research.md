on this page i will be adding my research

# research question
## how can i make the connection between client and server safer?

### subquestions/parts
- introduction
- what are the differences?
- how does https improve the safety?
- what do i need to upgrade http to https?
- how do i test the upgraded safety?
- why is security important?

## introduction
HTTP stands for hypertext transfer protocol. It is used to send information over the internet between a client and a server. However HTTP is not secure, this means anyone can see the message sent. This is ofcourse sub optimal for safety reasons. 

HTTPS stands for hypertext transfer protocol secure. It is the upgraded version of HTTP, it uses something called TLS, which stands for transport layer security. This is an encryption program, it encrypts the message sent between client and server.This encryption makes sure that outsiders cannot read or tamper with the data, even if/when they manage to intercept it.

By upgrading HTTP to HTTPS, a layer of security is added. When someone tries to look at the message sent from client to server through a program like wireshark they can see the entire HTTP message plain as day. With HTTPS you could only see an encrypted message.

For developers working on web-based applications, projects using web servers or any other IOT projects, security is essential. Whether you're building a scoreboard system, a login form, or controlling hardware remotely, upgrading from HTTP to HTTPS adds a necessary layer of protection.

This upgrade improves not only the security of the system, but also trustworthiness, if others will interact with or use the application. It shows the developer cares about data privacy and modern web standards.

# upgrading HTTP to HTTPS
what do you need to upgrade HTTP to HTTPS?
- ssl/tls certificate
- https capable server
- updated URL's

### sources
https://www.cloudflare.com/learning/ddos/glossary/hypertext-transfer-protocol-http/
https://www.ssl.com/faqs/what-is-https/