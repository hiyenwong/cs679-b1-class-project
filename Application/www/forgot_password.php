<?php
	require_once '../includes/config.inc';
	
	if (!empty($_POST)){
	
	}
	
	$smarty = new MySmarty($SMARTY_CONFIG);
	$smarty->display('forgot_password.tpl');
	
?>