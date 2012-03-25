<?php
	require_once '../includes/config.inc';
	
	session_start();
	session_destroy();
	$smarty = new MySmarty($SMARTY_CONFIG);
	//$smarty->assign('left_menu', true);	
	$smarty->display('logout.tpl');
	
?>