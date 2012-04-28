{include file='header.tpl'}

<script type="text/javascript" src="{$js_url}/validation.js"></script>
<script type="text/javascript" src="{$js_url}/register.js"></script>

<div id="header_wrap{if !$homepage}_secondary{/if}">
    <div id="header{if $secondary}_secondary{/if}"><!-- begin header -->
       
       {include file='upperheader.tpl' user=$user}
        
        <div id="header_lower">	   
            <div id="header_sub_secondary"> 
                <div id="header_sub_text_secondary">
                    <p>Registration</p>           
                </div>
            </div>
            <div id="header_sub_secondary_right">
               Creating an account is fast, easy and free
            </div>                            
        </div><!-- end header lower-->
    </div><!-- end header -->
</div>
    
<div id="page{if !$homepage}_secondary{/if}"><!-- start page content -->
    
    <div id="main_content">
        <div id="main_content_left_secondary">
            <fieldset id="register">
                <legend>Create an account</legend>
                <form action="register.php" method="POST">
                    <input type="hidden" name="action" value="adduser" />
                    <div id="register_user_password" class="register_toggle">
                        <p><label for="username">Email: </label><input type="email" name="username" id="username" class="user_password"><span class="success"></span><span class="error"></span></p>
                        <p><label for="password">Password: </label><input type="password" name="password" id="password" class="user_password"><span class="error"></span></p>
                        <p><label for="password_repeat">Confirm Password: </label><input type="password" name="password_repeat" id="password_repeat" class="user_password"><span class="error"></span></p>
                        <p><input type="button" name="next" id="next" value="Next"></p>
                    </div>
                    <div id="register_name" class="register_toggle">
                        <p><label for="firstname">First Name: </label><input type="text" name="firstname" id="firstname"><span class="error"></span></p>
                        <p><label for="lastname">Last Name: </label><input type="text" name="lastname" id="lastname"><span class="error"></span></p>
                        <p><input type="submit" name="submit" value="Register"></p>
                    </div>
                </form>
            </fieldset>
            
        </div><!-- end main content left  -->
    </div> <!-- end main content  -->
    <div class="clear">&nbsp;</div>       
    
</div>
<div class="push"></div>

{include file='footer.tpl'}
