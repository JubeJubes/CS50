select distinct(name) from ratings
join directors on ratings.movie_id = directors.movie_id
join people on directors.person_id = people.id
where rating >= 9;