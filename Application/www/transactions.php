<?php
	require_once '../includes/config.inc';
	require_once 'user.inc';
	require_once 'access.inc';
	require_once 'activity.inc';
	require_once 'accessdeniedexception.inc'; 
	require_once 'category.inc';
	require_once 'transaction.inc';
	
	$access = new Access();
	$access->authenticate();
	$user = $access->getUser();

	//var_dump($_POST['data']['transdate']); exit;
	if (!empty($_POST)) {
		switch ($_POST['action']) {
			case 'edit':
				$transaction = new Transaction(new MySqlDB());
				$transaction->start();
				
				$activity = Factory::getView(new ActivityKey($_POST['data']['id']));
				$activity->setName($_POST['data']['name']);
				
				$activity->setCategory(Factory::getView(new CategoryKey($_POST['data']['category'])));
				//var_dump($activity->getCategory());exit;
				$activity->setTransactionDate((date('Y-m-d H:i:s', strtotime($_POST['data']['transdate']))));
				$activity->setAmount($_POST['data']['amount']);
				$transaction->commit();
				break;
			case 'remove':
				echo $_POST['data']['id'];
				print_r($_POST); exit;
				$transaction = new Transaction(new MySqlDB());
				$transaction->start();
				
				$activity = Factory::getView(new ActivityKey($_POST['data']['id']));
				$activity->delete();
				$transaction->commit();
				break;
			case 'create':
				$transaction = new Transaction(new MySqlDB());
				$transaction->start();
				
				$activity = Factory::createView(new ActivityKey());
				$activity->setUser($user);
				$activity->setImportNumber(-1);
				$activity->setImportTime(date('Y-m-d'));
				
				$activity->setName($_POST['data']['name']);
				
				//$activity->setCategory(Factory::getView(new CategoryKey($_POST['data']['category'])));
				//var_dump($activity->getCategory());exit;
				$activity->setTransactionDate((date('Y-m-d H:i:s', strtotime($_POST['data']['transdate']))));
				$activity->setAmount($_POST['data']['amount']);
				$transaction->commit();
				break;
		}
		echo json_encode('success');
		return;
	}
	
	
	try {
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