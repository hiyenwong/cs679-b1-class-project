<?php
	require_once '../includes/config.inc';
	require_once 'user.inc';
	require_once 'access.inc';
	require_once 'accessdeniedexception.inc';
    require_once 'category.inc';
    require_once 'budget.inc';
    require_once 'factory.inc';
    require_once 'view.inc';
    require_once 'transaction.inc';

	try {
		$access = new Access();
		$access->authenticate();
		$user = $access->getUser(); 		
    	$smarty = new MySmarty($SMARTY_CONFIG);
    		
    	$userCategories = Category::getOptions(array("USER_ID" => $user->getId()));
    	$allCategories = Category::getOptions();
    		
    	$budgets = Budget::getOptions(array("USER_ID" => $user->getId(), "ACTIVE" => 1));
    		
    	$smarty->assign('budget', $budgets);
    	$smarty->assign('allCategories', $allCategories);
    	$smarty->assign('userCategories', $userCategories);
    	$smarty->assign('user', $user);
    	$smarty->assign('left_menu', true);
    	$smarty->display('chart.tpl');
		
	} catch (AccessDeniedException $e) {
		trigger_error('Access Denied');
	} catch (Exception $e) {
		//trigger_error('An error has occurred, please try again in a few minutes');
		print_r($e);
	}
	
?>