<?php
	require_once '../includes/config.inc';
	
	$smarty = new MySmarty($SMARTY_CONFIG);
	$smarty->assign('left_menu', true);	
	$smarty->assign('about', 'about');
	$smarty->display('about.tpl');
	
?>