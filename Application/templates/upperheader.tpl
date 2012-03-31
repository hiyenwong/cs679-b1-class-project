<div id="header_upper">
	<div id="header_logo"></div>
		     
 	<div id="navs"><!-- begin navigations -->
   		<div id="navs_left"></div>
   		<div id="navs_center">
     		<ul>
         		<li><a href="index.php">Home</a></li>
    	    	<li><a href="about.php">About</a></li>
    	    	<li><a href="contact.php">Contact</a></li>
    	    	{if !$user}
    	    	<li><a href="login.php">Log In</a></li>
    	    	<li><a href="register.php">Register</a></li>
    	    	{else}
    	    	<li><a href="userpage.php">Dashboard</a></li>
    	    	<li><a href="logout.php">Log Out</a></li>
    	    	{/if}
    	    	
   			</ul>
   		</div>
		<div id="navs_right"> </div>
	</div><!-- end navigations -->
</div><!-- end header upper -->