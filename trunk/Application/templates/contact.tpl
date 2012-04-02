{include file='header.tpl'}

<div id="header_wrap{if !$homepage}_secondary{/if}">
	<div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
		{include file='upperheader.tpl' user=$user}
	  
	  	{if $user}{include file='lowerheader.tpl'}{/if}
	</div><!-- end header -->
</div>

{literal}
<script type="text/javascript">
$(document).ready(function(){
	$("input[type=submit]").click(function(e){
		if ($("#name").val() == ''){
			$("p.error").html('Please enter your name.');
			e.preventDefault();
			$("#name").focus();
		} else if ($("#email").val() == ''){
			$("p.error").html('Please enter an email address.');
			e.preventDefault();
			$("#email").focus();
		} else if (!(/^[_a-z0-9]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3})$/i.test($("#email").val()))) {
			$("p.error").html('Please enter a valid email address.');
			e.preventDefault();
			$("#email").focus();
		} else if ($("#message").val() == ''){
			$("p.error").html('Please enter your message.');
			e.preventDefault();
			$("#message").focus();
		}
	})
});
</script>
{/literal}

<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
    
	<div id="main_content" style="height: 430px">
		<div id="main_content_left_secondary">
       		<fieldset id="contact">
       			<div id="status">{if $message}{$message}{/if}</div>
	       		<legend>Please fill out the form below:</legend>
                <form id='contactus' method="post" action="contact.php">
                	<p class="error"></p>
                    <p><label for="name">Name: </label><input type="text" name="name" id="name" {if $user}value="{$user->getFirstName()} {$user->getLastName()}"{/if}></p>
	        		<p><label for="email">Email: </label><input type="email" name="email" id="email" {if $user}value="{$user->getUsername()}"{/if}></p>
	        		<p><label for="message">Message: </label><textarea name = "message" id="message"></textarea></p>
	        		<p><input type="submit" name="submit" value="Send"></p>
                </form>
        	</fieldset>
		</div><!-- end main content left  -->
    </div> <!-- end main content  -->
	<div style="clear: both;">&nbsp;</div>                
</div>

{include file='footer.tpl'}
