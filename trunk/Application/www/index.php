<?php
	require_once '../includes/config.inc';
	
	$smarty = new MySmarty($SMARTY_CONFIG);
	$smarty->assign('homepage', 'homepage');
	$smarty->display('index.tpl');
	
?>