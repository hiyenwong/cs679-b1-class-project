# How to set up your environment #

Information for Windows, MAC, and Linux

# Windows #
There are variety of ways to set up your environment in Windows, One way is use an all in one package such as WAMP, or if you are an experience user, set up each individual component (Apache, MySQL, and PHP), lastly is to you an online service (don't recommend this).

WAMP (Windows, Apache, MySQL, PHP): This is an AIO package
  * http://www.wampserver.com/en/
  * As basic as follow the installation dialog

Apache, MySQL, PHP, individual install
  * Install MySQL First, you can download it here: http://www.mysql.com/downloads/installer/
  * Follow the installation dialog, and when it ask you what type of database, select transactional (INNODB)
  * Installing Apache next, get your package here: http://httpd.apache.org/download.cgi, I recommend version 2.2
  * Installing is basic, follow the direction.
  * Configuring Apache is the more difficult part.
  * This link should give you all the details on to configure all three things: http://www.bicubica.com/apache-php-mysql/index.php
  * PHP is simplely downloading it and unzipping it, and copy php.ini into your windows directory, copy two dll to the Apache directory and you are done.

Finally you have hosted environment. Put these involve paying for the service and really not necessary for what we need.


# MAC #
MAMP (Mac, Apache, MySQL, PHP): This is an AIO package, and its what I use on my Mac.
  * You can get it here: http://www.mamp.info/en/index.html
  * Installation is simple as dragging it and dropping it into you applications.
  * Configuring it is as simple as answer a few questions on the GUI screen.

If you prefer to install each individual component, you can find more information here. But it is almost identical to the Windows installation instructions.
  * This seems to be the best instructions I found: http://www.klauskomenda.com/archives/2008/10/07/installing-apache-mysql-and-php-on-leopard/


# Linux #
XAMPP (LinuX, Apache, MySQL, PHP, Perl)
  * Find the package here: http://www.apachefriends.org/en/xampp.html

Because of so many different linux distro, I am going to speak in very general terms. In my cases, I would recommend you installing from your package manager because they do behind the scene configuration which make configuring things that much easier.
  * Installing MySQL, Download it from the source and install it, or use your package manager to install it.
  * Apache Installation. You can either download from the source, http://httpd.apache.org, or use your package manager to install this.
  * PHP can be download from php.net or use package manager.


# Last Note #
Finally when you have your environment setup, you can download the source for our project.