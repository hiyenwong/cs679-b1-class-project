<?php
require_once '../includes/config.inc';
require_once 'user.inc';
require_once 'access.inc';
require_once 'accessdeniedexception.inc';
require_once 'activity.inc';
require_once 'category.inc';
require_once 'budget.inc';
require_once 'factory.inc';
require_once 'view.inc';
require_once 'transaction.inc';
require_once 'date.inc';

$func = isset($_REQUEST['func']) ? htmlentities($_REQUEST['func']) : false;
$chart = isset($_REQUEST['chart']) ? htmlentities($_REQUEST['chart']) : false;

try {
	$access = new Access();
	$access->authenticate();
	$user = $access->getUser();
		
	if ($func && $chart && $func == 'getData' && $chart == 'pie') {
		$today = new Date();
		$firstDayOf6MonthsAgo = new Date($today->format("%Y") . ($today->format("%m") - 6) . '-01');
		
		// Summing up the activities per month
		$activities = array();
		foreach ($user->getActivities() as $activity) {
			if (array_key_exists($activity->getTransactionDate()->format('%Y-%m'), $activities)) {
				$activities[$activity->getTransactionDate()->format('%Y-%m')] += $activity->getAmount();
			} else {
				$activities[$activity->getTransactionDate()->format('%Y-%m')] = $activity->getAmount();
			}
		}
		
		$results = array();
		foreach ($activities as $date => $amount) {
			$results[] = array('c' => array(array('v' => $date), array('v' => abs($amount))));
		}
		
		echo json_encode(array('cols' => array(
									array('id'=>'transaction_date', 'label'=>'Transaction Date', 'type'=>'string'),
									array('id'=>'amount', 'Label'=>'Amount', 'type'=>'number')),
						'rows' => $results));
	} else {
		
		$smarty = new MySmarty($SMARTY_CONFIG);
		$smarty->assign('user', $user);
		
		$smarty->assign('left_menu', true);
		$smarty->display('chart.tpl');
	}
	
} catch (AccessDeniedException $e) {
	trigger_error('Access Denied');
} catch (Exception $e) {
	//trigger_error('An error has occurred, please try again in a few minutes');
	print_r($e);
}
	
?>