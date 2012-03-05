<?php
	require_once '../Application/includes/config.inc';
	
	$smarty = new MySmarty($SMARTY_CONFIG);
	
	$smarty->display('accounts.tpl');
	
?>