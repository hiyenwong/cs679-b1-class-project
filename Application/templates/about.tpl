{include file='header.tpl'}
<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		<div id="header_upper">
			<div id="header_logo"></div>	     
	     	
	     	<div id="navs"><!-- begin navigations -->
	       		<div id="navs_left"></div>
	       		<div id="navs_center">
	         		<ul>
	             		<li><a href="index.php">Home</a></li>
	        	    	<li><a href="about.php" class="current">About</a></li>
	              	  	<li><a href="contact.php">Contact</a></li>          	    	
	               	  	<li><a href="login.php">Log In</a></li>     
	                	<li><a href="register.php">Register</a></li>     
	       			</ul>
	       		</div>
	   			<div id="navs_right"> </div>
	  		</div><!-- end navigations -->
	 	</div><!-- end header upper -->
	  
	  	<div id="header_lower">	   
		 	<div id="header_sub_secondary"> 
		    	<div id="header_sub_text_secondary">
		    		<p>About us</p>           
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
       		<h1>A bit about our company</h1>
        	<h5>Our company specializes in software projects that are handled from conception to maintenance. Our office is based in Boston, Massachusetts. </h5>
			<br><br>
			<p>Our goals</p>
			<ul><li>Create applications that are in best concordance with the client's needs.</li>
				<li>Have a collaborative approach with partners and clients.</li>
				<li>Create a comfortable atmosphere for our employees to work in.</li></ul>
			
          	<p>Our values</p>
			<ul><li>Team spirit: working together to achieve our goals.</li>
				<li>Communication with the client and inside the project team.</li>
				<li>Commitment from the beginning to the end of every project.</li></ul>
          
          	<div class="page_column">
           		<h4>About the team</h4>
            	<p><img width="100" height="100" class="img" alt="compass" src="images/compass.png">
            	 Our team for the iBudget project is composed of 6 people with all different backgrounds and responsibilities
            	 like project leader, quality leader, implementation leader etc...</p>
            	 <a href="#">Read More...</a></p>
          	</div>
          
          	<div class="page_column">
            	<h4>About the project</h4>
            	<p><img width="100" height="100" class="img" alt="parcel" src="images/parcel.png">The iBudget project is a web application that enables you to manage your financial expenses. You can personalize all your uploaded statements by putting them in any category you have created. That way, you can see the evolution of your finances the way you think is best. <a href="#">Read More...</a></p>
          	</div>
                    
		</div><!-- end main content left  -->
      		<!-- end main content right  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
