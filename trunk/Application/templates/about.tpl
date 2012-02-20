{include file='header.tpl'}
<div id="header_wrap{if $secondary}_secondary{/if}">
            <div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
                <div id="header_upper">
                    
                  <div style="cursor:pointer;" onclick="location.href='index.html';" id="header_logo"></div>
                    
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
		
		<div id="page{if $secondary}_secondary{/if}"><!-- start page content -->
            
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
                    <h5>Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Proin sed odio et ante adipiscing lobortis. Quisque eleifend, arcu a dictum varius, risus neque venenatis arcu, a semper massa mi eget ipsum. </h5>
      				  <p>Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Proin sed odio et ante adipiscing lobortis. Quisque eleifend, arcu a dictum varius, risus neque venenatis arcu, a semper massa mi eget ipsum. Proin sed odio et ante adipiscing lobortis. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Proin sed odio et ante adipiscing lobortis. Quisque eleifend, arcu a dictum varius, risus neque venenatis arcu, a semper massa mi eget ipsum. Proin sed odio et ante adipiscing lobortis.</p>
                      <p>Quisque eleifend, arcu a dictum varius, risus neque venenatis arcu, a semper massa mi eget ipsum. Proin sed odio et ante adipiscing lobortis. Proin sed odio et ante adipiscing lobortis. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Proin sed odio et ante adipiscing lobortis.</p>
                      
                      <div class="page_column">
                        <h4>Sub-Column Text</h4>
                        <p><img width="100" height="100" class="img" alt="compass" src="images/compass.png">Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Proin sed odio et ante adipiscing lobortis. Quisque eleifend, arcu a dictum varius, <a href="#">Read More...</a></p>
                      </div>
                      
                      <div class="page_column">
                        <h4>Sub-Column Text</h4>
                        <p><img width="100" height="100" class="img" alt="parcel" src="images/parcel.png">Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Proin sed odio et ante adipiscing lobortis. Quisque eleifend, arcu a dictum varius, <a href="#">Read More...</a></p>
                      </div>
                      
				</div><!-- end main content left  -->
        		<!-- end main content right  -->
        	</div> <!-- end main content  -->
          <div style="clear: both;">&nbsp;</div>       
            
        </div>
        <div class="push"></div>

{include file='footer.tpl'}
