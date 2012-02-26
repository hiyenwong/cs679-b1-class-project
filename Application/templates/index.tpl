{include file='header.tpl'}

		<div id="header_wrap">
			<div id="header"><!-- begin header -->
				<div id="header_upper">
						
					<div style="cursor:pointer;" onclick="location.href='index.html';" id="header_logo"></div>
						
					<div id="navs"><!-- begin navigations -->
						<div id="navs_left"></div>
						<div id="navs_center">
							<ul>
								<li><a href="index.php" class="current">Home</a></li>
								<li><a href="about.php">About</a></li>
								<li><a href="contact.php">Contact</a></li>	 
								<li><a href="login.php">Log In</a></li>	 
								<li><a href="register.php">Register</a></li>	 
							</ul>
						</div>
						<div id="navs_right"></div>
					</div><!-- end navigations -->
				</div><!-- end header upper -->
					
				<div id="header_lower">	

					<div class="slider-wrap"><!-- begin slider -->
						<div class="slider">
							<div id="jFlowSlide" style="position: relative; width: 495px; height: 255px; overflow: hidden;">
								<div id="mySlides" style="position: relative; width: 1485px; height: 255px; overflow: hidden; margin-left: -495px;">
									<!-- slider 1 -->
									<div class="jFlowSlideContainer"><img alt="slide1" src="{$image_url}/excel_apps.jpg"></div>
									
									<!-- slider 2 -->
									<div class="jFlowSlideContainer"><img alt="slide2" src="{$image_url}/economic_growth.jpg"></div>	
									
									<!-- slider 3 -->
									<div class="jFlowSlideContainer"><img alt="slide3" src="{$image_url}/family_budget.jpg"></div>
								</div>
							</div>
						</div>
					</div><!-- end slider wrap -->
					
					<div id="header_sub">
						<div id="header_sub_headline">
							<h1>Welcome to iBudget</h1>
							<h2>A new way to manage your expences and keep track of where your money goes.</h2>
						</div>
						<div id="header_sub_port">
							<div id="header_sub_text">
								<h3>Want to see more?</h3>
								<h4>Please take that enthusiasm with you to the projects page!</h4>
							</div>
							<div id="header_sub_button">
								<a href="projects.html"><img width="50" height="50" class="go_button" alt="Go To Project" src="{$image_url}/go-button.jpg"></a>
							</div>
						</div><!-- header sub port -->
					</div><!--end header sub-->
					
					<div class="slider_nav"><!-- slider navigation -->
						<div class="slider_nav_left">
							<div id="myController">
								<span class="jFlowControl">1</span>
								<span class="jFlowControl">2</span>
								<span class="jFlowControl">3</span>
							</div>
						</div>
					</div><!-- end slider navigation-->
			  
				</div><!-- end header lower-->
			</div><!-- end header -->
		</div>

		<div id="page"><!-- start page content -->
			<div id="sub_boxes"><!-- start sub boxes  --> 
				
				<!-- sub box 1 -->
				<div class="sub_box">
					<div class="sub_box_text">
						<img width="40" height="40" class="sub_box_image" style="vertical-align:middle" alt="briefcase" src="{$image_url}/speed.png"><h2>Speed</h2>
						<p>List here the benefits of feature1. </p>
						<p><a href="#">Read more <img width="20" height="20" style="vertical-align:top" alt="" src="{$image_url}/arrow_right.png"></a></p>
					</div>
				</div>
				
				<!-- sub box 2 -->
				<div class="sub_box">
					<div class="sub_box_text">
						<img width="40" height="40" class="sub_box_image" style="vertical-align:middle" alt="display" src="{$image_url}/shield.png"><h2>Information Safety</h2>
						<p>List here the benefits of feature2 </p>
						<p><a href="#">Read more <img width="20" height="20" style="vertical-align:top" alt="" src="{$image_url}/arrow_right.png"></a></p>
					</div>
				</div>
				
				<!-- sub box 3 -->
				<div class="sub_box_right">
					<div class="sub_box_text">
						<img width="40" height="40" class="sub_box_image" style="vertical-align:middle" alt="rolodex" src="{$image_url}/danger.png"><h2>Growth</h2>
						<p>List here the benefits of feature3 </p>
						<p><a href="#">Read more <img width="20" height="20" style="vertical-align:top" alt="" src="{$image_url}/arrow_right.png"></a></p>
					</div>
				</div>
			</div><!-- end sub boxes  -->
			
			<div id="main_content">
				<div id="main_content_left">
					<h1>A bit about the iBudget project</h1>
					<p>The iBudget project started out as a group project for a software engineering class. After we completed it and showed it to some of our friends we realized the big potential it has and the
					bumerous benefits it provides to users. We decided to launch the project... </p>
					
					<blockquote>
						<p>"If you need motivation to achieve financial discipline, consider iBudget. It has all the features I need and is very intuitive and easy to use."</p>
						<p><i> -- Tom Smith</i></p>
					</blockquote>
					<p>Some more text over here </p>
				</div><!-- end main content left  -->

				<div id="main_content_right">
					<h2 class="sub_box_text"><img width="27" height="24" class="sub_box_image" style="vertical-align:middle" alt="resources" src="{$image_url}/resources.jpg">Resources and helpful links</h2>
					<p>Here we provide helpful links.</p> 
					<ul>
						<li><a href="http://www.fpanet.org/">Financial Planning Association</a></li>
						<li><a href="http://www.moneysaveronline.com/">Money Saver Magazine</a></li>
						<li><a href="http://www.saveandinvest.org/">Save and Invest</a></li>
					</ul>
				</div><!-- end main content right  -->
				
			</div><!-- end main content  -->
			<div style="clear: both;">&nbsp;</div>
		</div>
		<div class="push"></div>

		<script type="text/javascript">
		$(document).ready(function(){
			$("#myController").jFlow({
				slides: "#mySlides",
				width: "495px",
				height: "255px",
				duration: 400
			});
		});
		</script>

{include file='footer.tpl'}
