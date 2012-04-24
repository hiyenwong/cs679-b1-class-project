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

$action = isset($_REQUEST['action']) ? htmlentities($_REQUEST['action']) : false;
$data = isset($_REQUEST['data']) ? $_REQUEST['data'] : false;

try {
	if ($action) {
		if ($data === false) {
			throw new Exception("Missing required parameter data");
		}
		
		switch ($action) {
			case 'edit':
				$transaction = new Transaction(new MySqlDB());
				$transaction->start();
				
				$activity = Factory::getView(new ActivityKey($data['id']));
				$activity->setName($data['name']);
				
				if ($data['category'] != null && trim($data['category']) && $data['category'] != 'null') {
					$activity->setCategory(Factory::getView(new CategoryKey(trim($data['category']))));
				}
				$activity->setTransactionDate(new Date($data['transdatr']));
				$activity->setAmount($data['amount']);
				$transaction->commit();
				break;
			case 'remove':
				if (!array_key_exists('id', $_REQUEST) || !trim($_REQUEST['id'])) {
					throw new Exception("Missing required parameter transaction id");
				}
				
				$transaction = new Transaction(new MySqlDB());
				$transaction->start();
				
				$activity = Factory::getView(new ActivityKey($_REQUEST['id']));
				$activity->requestDelete();
				$transaction->commit();
				break;
			case 'create':
				$transaction = new Transaction(new MySqlDB());
				$transaction->start();
				
				$date = new Date();
				
				$activity = Factory::createView(new ActivityKey());
				$activity->setUser($user);
				$activity->setImportNumber(-1);
				$activity->setImportTime($date);
				$activity->setName($data['name']);
				$activity->setTransactionDate($date);
				$activity->setAmount($_POST['data']['amount']);
				
				if ($data['category'] != null && trim($data['category']) && $data['category'] != 'null') {
					$activity->setCategory(Factory::getView(new CategoryKey(trim($data['category']))));
				}
				
				$transaction->commit();
				break;
		}
		echo json_encode(array('success'=>'true'));
	} else {

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
	}
	
} catch (AccessDeniedException $e) {
	header ('HTTP/1.1 401 Access Denied');
	echo "AccessDeniedException: " . $e->getMessage ();
} catch (Exception $e) {
	if ($transaction && !$transaction->isComplete ()) {
		$transaction->rollback ();
	}
	header ('HTTP/1.1 500 Internal Server Error');
	echo "Exception: " . $e->getMessage ();
}
?>