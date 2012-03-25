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
						{if !$username}<a href="login.php">Log In</a> | {else} <a href="logout.php">Log Out</a> {/if}
						{if !$username}<a href="register.php">Register</a>{/if} 		
					</div>
				</div>
			</div>
		</div>
</body>
</html>