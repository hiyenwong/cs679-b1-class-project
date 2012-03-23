<?php
	session_start();
	require_once '../includes/config.inc';

	$smarty = new MySmarty($SMARTY_CONFIG);

	$smarty->assign('username', $_SESSION['user']);
	$smarty->assign('left_menu', true);
	$smarty->display('userpage.tpl');
	
?>