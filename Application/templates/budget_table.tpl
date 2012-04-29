<table>
    <thead>
        <tr>
            <th>Category</th>
            <th>Budgeted</th>
            <th>Spent</th>
            <th>Amount Left</th>
            <th>&nbsp;</th>
        </tr>
    </thead>
    <tbody id="budgetRows">
        {foreach from=$budgets key=k item=v}
            <tr>
                <td>{$v.name}</td>
                <td>${$v.amount}</td>
                <td>${$spent.$k}</td>
                <td>${$budgetLeft.$k}</td>
                <td><input type="button" value="Remove" onclick="removeBudgetItem(this, {$k})" /></td>
            </tr>
        {/foreach}                    
    </tbody>
</table>