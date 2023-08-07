select title from ratings
join movies on ratings.movie_id = movies.id
join stars on movies.id = stars.movie_id
join people on people.id = stars.person_id
where name = 'Chadwick Boseman' order by rating desc limit 5;