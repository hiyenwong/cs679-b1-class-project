<div id="header_lower">	   
 	<div id="header_sub_secondary"> 
    	<div id="header_sub_text_secondary">
    		<p>{if $user->getFirstName() || $user->getLastName()}{$user->getFirstName()} {$user->getLastName()}{else}{$user->getUsername()}{/if}{if $title}'s {$title}{/if}</p>           
  		</div>
   	</div>
    <div id="header_sub_secondary_right">{$message}</div>                            
</div><!-- end header lower-->