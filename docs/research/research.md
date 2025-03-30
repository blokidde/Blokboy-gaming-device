on this page i will be adding my research

# research question
## how can i make the entire connection between client and server safer?

## introduction
HTTP stands for hypertext transfer protocol. it is used to send information over the internet between a client and a server. However HTTP is not secure, this means anyone can see the message sent. This is ofcourse sub optimal for safety reasons. 

HTTPS stands for hypertext transfer protocol secure. it is the upgraded version of HTTP, it uses something called TLS, which stands for transport layer security. this is an encryption program, it encrypts the message sent between client and server. 

by upgrading HTTP to HTTPS, a layer of security is added. when someone tries to look at the message sent from client to server through a program like wireshark they can see the entire HTTP message plain as day. with HTTPS you could only see a 

# upgrading HTTP to HTTPS
what do you need to upgrade HTTP to HTTPS?
- ssl/tls certificate
- https capable server
- updated URL's

### sources
https://www.cloudflare.com/learning/ddos/glossary/hypertext-transfer-protocol-http/
https://www.ssl.com/faqs/what-is-https/