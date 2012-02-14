<div class="search-result" id="{$result->getId()}">
	{if $result->getRowCount() > 0 && !$disable_excel}
	<div style="padding-bottom: 1em;">
		<span style="font-weight: bold;">{$result->getRowCount()}</span> Result{if $result->getRowCount() > 1}s{/if} |
		{if $result->isPaged()}
			<span style="font-weight: bold;">{$result->getPageCount()}</span> Page{if $result->getPageCount() > 1}s{/if} |
		{/if}
		<img class="attachment" src="{$image_url}/excel.png" /> <a href="{$result->getUrl()}&mysortorder=desc&mysortheader={$headers[i]}&export=xls">Export to Excel</a>
		{if $result->getRowCount() < 250} |{if $result->isPaged()}<a href="{$result->getUrl()}&paged=false">Show All</a>{else}<a href="{$result->getUrl()}">Show Paged</a>{/if}{/if}
	</div>
	{/if}

	<table class="panel">
		<thead>
			<tr>
				{assign var=headers value=$result->getHeaders()}
				{assign var=count value=$result->getHeaderCount()}
				{assign var=mycounter value=0}
				{section name=i loop=$headers}
					{if $result->getDoSort()}
						{if $result->getSortOrder() == "asc"}
						<th><a href="{$result->getUrl()}&mysortorder=desc&mysortheader={$headers[i]}{if !$result->isPaged()}&paged=false{/if}">{$headers[i]}</a></th>
						{else}
						<th><a href="{$result->getUrl()}&mysortorder=asc&mysortheader={$headers[i]}{if !$result->isPaged()}&paged=false{/if}">{$headers[i]}</a></th>
						{/if}
					{else}
						<th>{$headers[i]}</th>
					{/if}
					{assign var=mycounter value=$mycounter+1}
				{/section}
			</tr>
		</thead>

		<tbody>
			{if $result->isPaged() && $result->getPageCount() > 1}
				{if $smarty.request.page}
					{assign var=page value=$smarty.request.page}
				{else}
					{assign var=page value=1}
				{/if}
				{assign var=rows value=$result->getPage($page)}
			{else}
				{assign var=rows value=$result->getRows()}
			{/if}

			{section name=i loop=$rows}
				{if $smarty.section.i.iteration % 2 == 1}
					<tr class="odd">
				{else}
					<tr class="even">
				{/if}

				{section name=j loop=$headers}
					{assign var=row value=$rows[i]}
					{assign var=header value=$headers[j]}
					{if is_array($row[$header])}
						{assign var=elements value=$row[$header]}
						<td>
							{section name=k loop=$elements}
								{$elements[k]}<br />
							{/section}
						</td>
					{else}
						{if is_a($row[$header], "SearchElement") || is_a($row[$header], "Date")}
							<td nowrap>
						{else}
							<td>
						{/if}
								{$row[$header]}
							</td>
					{/if}
				{/section}
				</tr>
			{sectionelse}
				<tr class="odd">
					<td class="none" colspan="{$count}">None</td>
				</tr>
			{/section}
		<tbody>

		<tfoot></tfoot>
	</table>
</div>

{if $result->isPaged() && $result->getPageCount() > 1}
<div class="searchpages" style="margin-top: 20px;">
	{$count = $result->getPageCount()}

	{$link = $result->getNonPagedLink()}
	<a href="{$PHP_SELF}?{$link}&page=1">&laquo;</a>&nbsp;

	{if $page - 5 < 1}
		{$start = 1}
	{else}
		{$start = $page - 5}
	{/if}

	{if $page + 6 > $count}
		{$end = $count + 1}
	{else}
		{$end = $page + 6}
	{/if}

	{section name=i start=$start loop=$end step=1}
		{if $smarty.section.i.index == $page}
			<font style="font-weight: bold; font-size: medium">{$smarty.section.i.index}</font>&nbsp;
		{else}
			<a href="{$PHP_SELF}?{$link}&page={$smarty.section.i.index}">{$smarty.section.i.index}</a>&nbsp;
		{/if}
	{/section}

	<a href="{$PHP_SELF}?{$link}&page={$count}">&raquo;</a>
</div>
{/if}
