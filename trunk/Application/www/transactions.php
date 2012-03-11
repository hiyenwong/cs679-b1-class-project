<?php
	require_once '../includes/config.inc';
	
	$smarty = new MySmarty($SMARTY_CONFIG);
	
	$smarty->display('transactions.tpl');
	
?>