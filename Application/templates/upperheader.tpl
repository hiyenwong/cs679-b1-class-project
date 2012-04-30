<div id="header_upper">
	<div id="header_logo"></div>
		     
 	<div id="navs"><!-- begin navigations -->
   		<div id="navs_left"></div>
   		<div id="navs_center">
     		<ul>
         		<li><a href="{$BASE_URL}/index.php" {if $homepage}class="current"{/if}>Home</a></li>
    	    	<li><a href="{$BASE_URL}/about.php" {if $about}class="current"{/if}>About</a></li>
    	    	<li><a href="{$BASE_URL}/contact.php" {if $contact}class="current"{/if}>Contact</a></li>
    	    	{if !$user}
    	    	<li><a href="{$BASE_URL}/login.php" {if $login}class="current"{/if}>Log In</a></li>
    	    	<li><a href="{$BASE_URL}/register.php" {if $register}class="current"{/if}>Register</a></li>
    	    	{else}
    	    	<li><a href="{$BASE_URL}/dashboard.php" {if $dashboard}class="current"{/if}>Dashboard</a></li>
    	    	<li><a href="{$BASE_URL}/logout.php">Log Out</a></li>
    	    	{/if}
    	    	
   			</ul>
   		</div>
		<div id="navs_right"> </div>
	</div><!-- end navigations -->
</div><!-- end header upper -->