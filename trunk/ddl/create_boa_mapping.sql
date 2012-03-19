INSERT INTO mapping(name, starting_row) VALUES('Bank Of America', 8);

INSERT INTO mapping_detail
SELECT id, 'TRANSACTION_DATE', '0' FROM mapping WHERE name = 'Bank Of America';

INSERT INTO mapping_detail
SELECT id, 'NAME', '1' FROM mapping WHERE name = 'Bank Of America';

INSERT INTO mapping_detail
SELECT id, 'AMOUNT', '2' FROM mapping WHERE name = 'Bank Of America';