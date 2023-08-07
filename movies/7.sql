select title, rating from movies
join ratings on movies.id = ratings.movie_id
where year = 2010 and rating >=0
order by rating desc, title;