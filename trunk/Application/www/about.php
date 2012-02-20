<?php
	require_once '../includes/config.inc';
	
	$smarty = new MySmarty($SMARTY_CONFIG);
	$smarty->assign('secondary', 'secondary');
	//$smarty->clearCache('index.tpl');
	
	$smarty->display('about.tpl');
	
?>