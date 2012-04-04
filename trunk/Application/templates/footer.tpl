	</div>
	
	<div id="footer_wrap">
		<div id="footer">
			<div id="footer_left">
				iBudget&trade;
			</div>
			
			<div id="footer_right">
				<div id="footer_r">
					<a href="index.php">Home</a> | 
					<a href="about.php">About Us</a> | 
					<a href="contact.php">Contact</a> |
					{if !$user}<a href="login.php">Log In</a> | {else} <a href="logout.php">Log Out</a> {/if}
					{if !$user}<a href="register.php">Register</a>{/if} 		
				</div>
			</div>
		</div>
	</div>
	<script type="text/javascript" src="{$js_url}/jquery.flow.1.0.js"></script>
	<script type="text/javascript" src="{$js_url}/ibudget.js"></script>
	<script type="text/javascript" src="{$js_url}/Base64.js"></script>
</body>
</html>