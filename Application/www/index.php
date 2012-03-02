<?php
	require_once '../includes/config.inc';
	
	$smarty = new MySmarty($SMARTY_CONFIG);
	$smarty->assign('homepage', 'homepage');
	$smarty->assign('left_menu', 'none'); //quick and dirty way
	$smarty->display('index.tpl');
	
?>