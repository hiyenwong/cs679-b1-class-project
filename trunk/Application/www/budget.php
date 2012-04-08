<?php
	session_start();
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
		
	    if (!empty($_POST)) {
	       $categoryId = htmlentities($_POST['categoryId']);
	       echo "Category = ";
	       print_r($categoryId);
	       //TODO: check amount is valid
	       $budgetedAmount = htmlentities($_POST['budgetedAmount']);
        	    
        	    
	       $transaction = new Transaction(new MySqlDB());
           $transaction->start();
                
	       $budget = Factory::createView(new BudgetKey());
	       $category = Factory::getView(new CategoryKey($categoryId));
	       
	       $budget->setUser($user);
	       $budget->setActive(TRUE);
	       $budget->setAmount($budgetedAmount);
	       $budget->setCategory($category);
	       
	       $transaction->commit();
	       
	       echo "Success";
	          
	    } else {            		
    		$smarty = new MySmarty($SMARTY_CONFIG);
    		
    		$userCategories = Category::getOptions(array("USER_ID" => $user->getId()));
    		$allCategories = Category::getOptions();
    		
    		$budgets = Budget::getOptions(array("USER_ID" => $user->getId()));
    		
    		$smarty->assign('budgets', $budgets);
    		$smarty->assign('allCategories', $allCategories);
    		$smarty->assign('userCategories', $userCategories);
    		$smarty->assign('user', $user);
    		$smarty->assign('left_menu', true);
    		$smarty->display('budget.tpl');
		}
		
	} catch (AccessDeniedException $e) {
		trigger_error('Access Denied');
	} catch (Exception $e) {
		//trigger_error('An error has occurred, please try again in a few minutes');
		print_r($e);
	}
	
?>