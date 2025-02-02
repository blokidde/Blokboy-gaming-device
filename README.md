# IoT Start Project

This is your IoT Gitlab project. You can use it to store your code and documentation. 

## Getting Started

This project contains a setup using Docker. This will help you setup all the necessary tools to start developing your IoT project.
Before you run the docker-compose command, make sure you have to make changes to the configuration. You can find these in
the `.env` file.

Now, to install and start your project; run the following command in the root of your project:

```bash
docker-compose up -d
```

If everything runs correctly, you should be able to visit your website at [http://localhost/](http://localhost/).

## Structure

There is a specific structure that you should follow when developing your project. This will help you to keep your project organized and easy to understand.

**Documentation**

All the documentation of your project should be placed in the `docs/` folder. This will be used for your portfolio-website.

```bash
├── docs/
```


**Embedded**

Everything you need to run your embedded application should be placed in the `embedded/` folder. This includes the source code like .ino-files from Arduino.

```bash
├── embedded/
```


**Web**

Everything you need to run your web application should be placed in the `web/` folder. This includes the source code like PHP, HTML, CSS, Javascript and images.

```bash
├── web/
```

You can visit your website by going to [http://localhost/](http://localhost/) in your browser. And you can find your IoT dashboard at [http://localhost/dashboard](http://localhost/dashboard).

## Database details

The database is a MySQL database using MariaDB. You can connect to it using the following details:

| Parameter | Value |
| --- | --- |
| Host | `mariadb` (from PHP) `localhost` (from your laptop) |
| Port | `3306` |
| Username | `root` |
| Password | You can find this in your .env-file. |
| Database | You need to create the database yourself. |