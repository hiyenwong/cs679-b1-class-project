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
		    		<p>Vlad's Accounts</p>           
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
        		<li><a href="userpage.php">Overview</a>
            	</li>    	
        	    <li><a href="transactions.php">Transactions</a>
            	</li>
          	 	<li class="active"><a href="accounts.php">Accounts</a></li>
           	 	<li><a href="budget.php">Budget</a></li>
      		</ul>
   		</div>

		<div id="main_content_left_secondary">   
          	
                    
		</div><!-- end main content left  -->
      		<!-- end main content right  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>       
          
</div>
<div class="push"></div>

{include file='footer.tpl'}
