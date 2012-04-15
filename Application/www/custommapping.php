<?php
require_once '../includes/config.inc';
require_once 'access.inc';
require_once 'accessdeniedexception.inc';
require_once 'transaction.inc';
require_once 'factory.inc';
require_once 'view.inc';
require_once 'user.inc';
require_once 'mapping.inc';
require_once 'mappingdetail.inc';

try {
	$access = new Access();
	$access->authenticate();
	$user = $access->getUser();

	$transaction = false;
	
	if (array_key_exists('submitted', $_REQUEST) && $_REQUEST['submitted'] == 'Preview') {
		try {
			$return = array();
			
			if (($handle = fopen($_FILES['csv_file']['tmp_name'], "r")) !== FALSE) {
				$row = 0;
				while (($data = fgetcsv($handle, 1000, ",")) !== FALSE && $row < 20) {
					$row++;
					$return[] = $data;
				}
				fclose($handle);
			}
			
			echo base64_encode(json_encode(array('success' => 'yes', 'results' => $return)));
		} catch (Exception $e) {
			echo json_encode(array('success' => 'no'));
		}
		
	} else if (array_key_exists('submitted', $_REQUEST) && $_REQUEST['submitted'] == 'Save') {
		$startingRow = isset($_REQUEST['startingRow']) ? htmlentities($_REQUEST['startingRow']) : false;
		if ($startingRow === false) {
			throw new Exception('Missing required parameter starting row');
		}
		
		$name = isset($_REQUEST['name']) ? htmlentities($_REQUEST['name']) : false;
		if ($name === false) {
			throw new Exception('Missing required parameter custom mapping name');
		}
		
		$transactionDateCol = isset($_REQUEST['transactionDate']) ? htmlentities($_REQUEST['transactionDate']) : false;
		if ($transactionDateCol === false) {
			throw new Exception('Missing required parameter transaction date column');
		}
		
		$descriptionCol = isset($_REQUEST['description']) ? htmlentities($_REQUEST['description']) : false;
		if ($descriptionCol === false) {
			throw new Exception('Missing required parameter description column');
		}
		
		$amountCol = isset($_REQUEST['amount']) ? htmlentities($_REQUEST['amount']) : false;
		if ($amountCol === false) {
			throw new Exception('Missing required parameter amount column');
		}
		
		$transaction = new Transaction(new MySqlDB());
		$transaction->start();
		
		$mapping = Factory::createView(new MappingKey());
		$mapping->setUser($user);
		$mapping->setStartingRow($startingRow);
		$mapping->setName($name);
		$mapping->addMappingDetail(new MappingDetail($mapping, MappingDetail::$MAPPING_TRANSACTION_DATE, $transactionDateCol));
		$mapping->addMappingDetail(new MappingDetail($mapping, MappingDetail::$MAPPING_AMOUNT, $amountCol));
		$mapping->addMappingDetail(new MappingDetail($mapping, MappingDetail::$MAPPING_NAME, $descriptionCol));
		
		$transaction->commit();
		
	} else {
		$smarty = new MySmarty($SMARTY_CONFIG);
		$smarty->assign('user', $user);
		$smarty->assign('left_menu', true);
		$smarty->display('custommapping.tpl');
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