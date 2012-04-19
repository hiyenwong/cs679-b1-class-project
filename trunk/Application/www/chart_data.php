<?php
require_once '../includes/config.inc';
require_once 'user.inc';
require_once 'access.inc';
require_once 'category.inc';
require_once 'budget.inc';
require_once 'factory.inc';
require_once 'transaction.inc';
require_once 'activity.inc';

try {
		$access = new Access();
		$access->authenticate();
		$user = $access->getUser(); 		
    	$smarty = new MySmarty($SMARTY_CONFIG);
    		
    	$userCategories = Category::getOptions(array("USER_ID" => $user->getId()));
    	$json = '{
  		"cols": [
        {"id":"","label":"Category","pattern":"","type":"string"},
        {"id":"","label":"Amount","pattern":"","type":"number"}
      	],
  		"rows": [';
    	foreach ($userCategories as $value)
    	{
    		$json .= '{"c":[{"v":"'. $value['name'] .'",';
    		$sum = 0;
    		$activities = Activity::getOptions(array("USER_ID" => $user->getId(), "CATEGORY_ID" => $value['id']));
    		foreach ($activities as $value2)
    			$sum += 1;//$value2['amount'];
    		$json .= '"f":null},{"v":' . $sum . ',"f":null}]},';
    	} 	
    	$json = substr($json,0,-1);
		$json .= ']}';
		echo $json;
	} catch (AccessDeniedException $e) {
		trigger_error('Access Denied');
	} catch (Exception $e) {
		//trigger_error('An error has occurred, please try again in a few minutes');
		print_r($e);
	}
?>