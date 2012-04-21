<?php
	require_once '../includes/config.inc';
	require_once 'user.inc';
	require_once 'access.inc';
	require_once 'activity.inc';
	require_once 'accessdeniedexception.inc'; 
	require_once 'category.inc';
	require_once 'transaction.inc';

	
	try {
		$access = new Access();
		$access->authenticate();
		$user = $access->getUser();
		
		$smarty = new MySmarty($SMARTY_CONFIG);
		$smarty->assign('res', $user->getActivities());

	 	$userCategories = Category::getOptions(array("USER_ID" => $user->getId(), "ACTIVE" => 1));
        $allCategories = Category::getOptions(array("ACTIVE" => 1));
    	
        $categories = '';
        foreach($userCategories as $index=>$value) {
        	$categories .= "{\"value\": \"$index\", \"label\": \"$value\"},";     		
        }
        $smarty->assign('allCategories', $categories);
    		
		$smarty->assign('user', $user);
		$smarty->assign('left_menu', true);
		$smarty->assign('BASE_URL', $BASE_URL);
		$smarty->display('transactions.tpl');
	} catch (AccessDeniedException $e) {
		
	} catch (Exception $e) {
		
	}
	
	
	
	
	
?>