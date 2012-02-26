{include file='header.tpl'}
<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		<div id="header_upper">
	  		<div style="cursor:pointer;" onclick="location.href='index.php';" id="header_logo"></div>
	     
	     	<div id="navs"><!-- begin navigations -->
	       		<div id="navs_left"></div>
	       		<div id="navs_center">
	         		<ul>
	             		<li><a href="index.php">Home</a></li>
	        	    	<li><a href="about.php">About</a></li>
	        	    	<li><a href="contact.php">Contact</a></li>
	               	  	<li><a href="login.php" class="current">Log In</a></li>     
	                	<li><a href="register.php">Register</a></li>     
	       			</ul>
	       		</div>
	   			<div id="navs_right"> </div>
	  		</div><!-- end navigations -->
	 	</div><!-- end header upper -->
	  
	  	<div id="header_lower">	   
		 	<div id="header_sub_secondary"> 
		    	<div id="header_sub_text_secondary">
		    		<p>Log In</p>           
		  		</div>
		   	</div>
		    <div id="header_sub_secondary_right">
		      Intro message here
		    </div>                            
		</div><!-- end header lower-->
	</div><!-- end header -->
</div>

<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
          
	<div id="main_content">
		<div id="left_navigation">
    		<ul id="nav">
        		<li class="active"><img style="vertical-align:middle" alt="profile" src="images/Profile.png"><a href="#">Active Page</a>
            		<h2>Sub message can go here if you have one </h2>
            	</li>    	
        	    <li><img style="vertical-align:middle" alt="Pie Chart" src="images/Pie Chart.png"><a href="#">Sub Page 2</a>
            		<h2>Sub message can go here if you have one </h2>
            	</li>
          	 	<li><img style="vertical-align:middle" alt="Pie Chart" src="images/Modify.png"><a href="#">Sub Page Small</a></li>
           	 	<li><img style="vertical-align:middle" alt="Pie Chart" src="images/Email.png"><a href="#">Sub Page Small</a></li>
      		</ul>
   		</div>

		<div id="main_content_left_secondary">
       		<fieldset>
	       		<legend>Log In to iBudget</legend>
	        	<form action="login.php" method="POST">
	        		<p><label for="username">Username: </label><input type="text" name="username" id="username"></p>
	        		<p><label for="password">Password: </label><input type="password" name="password" id="password"></p>
	        		<a href="forgot_password.php" style="margin-left:180px">Forgot your password?</a>
	        		<p><input type="submit" name="submit" value="Log In"></p>
	        	</form>
        	</fieldset>
        	
        	<p>Don't have an account yet? Create one <a href="register.php">here</a></p>
                    
		</div><!-- end main content left  -->
      		<!-- end main content right  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
