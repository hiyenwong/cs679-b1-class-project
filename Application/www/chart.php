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
	
		$activities = array();
		foreach (Activity::getOptions(array(
					'USER_ID' => $user->getId(),
					'TRANSACTION_DATE_START' => $firstDayOf6MonthsAgo->format(Date::$SIMPLE_YEAR_MONTH_DAY),
					'TRANSACTION_DATE_END' => $today->format(Date::$SIMPLE_YEAR_MONTH_DAY))) AS $id => $value) {
			$transactionDate = new Date($value['transaction_date']);
			if (array_key_exists($transactionDate->format('%Y-%m'), $activities)) {
				$activities[$transactionDate->format('%Y-%m')] += $value['amount'];
			} else {
				$activities[$transactionDate->format('%Y-%m')] = $value['amount'];
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