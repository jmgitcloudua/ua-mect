using System.Data.SqlClient;

namespace BD2122
{
    internal class Class1
    {
        private SqlConnection con;

        private SqlConnection getSGBDConnection()
        {
            return new SqlConnection("data source= localhost;integrated security=true;initial catalog=Northwind");
        }

        public void listRecipiesByAuthor(string author)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText = "select * from recipie where recipie.author = @author";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@author", author);
            cmd.Connection = con;

            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                Console.WriteLine(reader.GetString(0) + " " + reader.GetString(1) + " " + reader.GetString(2) + " " + reader.GetString(3));
            }
        }

        public void listIngredients(string recipie)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText = 
                @"  select distinct ingredient.ingredientName
                    from
                    (
                        ingredient join usesIngredient
                        on ingredient.ingredientName = usesIngredient.ingredientName
                    ) join (
                        has join step
                        on has.stepID = step.stepID
                    ) on usesIngredient.stepID = step.stepID
                    where has.recipieName = @recipie; ";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@recipie", recipie);
            cmd.Connection = con;

            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                Console.WriteLine(reader.GetString(0));
            }
        }

        public void listUtensils(string recipie)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  select distinct usesUtensil.utensilName
                    from
	                usesUtensil
	                join (
		                has join step
		                on has.stepID = step.stepID
	                ) on usesUtensil.stepID = step.stepID
                    where has.recipieName = @recipie;";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@recipie", recipie);
            cmd.Connection = con;

            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                Console.WriteLine(reader.GetString(0));
            }
        }

        public void findByCategory(string category)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  select belongs.recipieName
                    from belongs 
                    where belongs.categoryName = @category;";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@category", category);
            cmd.Connection = con;

            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                Console.WriteLine(reader.GetString(0));
            }
        }

        public void findByAuthor(string author)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  select *
                    from recipie
                    where recipie.author = @author;";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@author", author);
            cmd.Connection = con;

            SqlDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                Console.WriteLine(reader.GetString(0));
            }
        }

        public void insertRecipie(string recipieName, string author, int calories, int preparingTime)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  insert into recipie
                    (recipieName, author, calories, preparingTime)
                    values
                    (@recipieName, @author, @calories, @preparingTime);";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@recipieName", recipieName);
            cmd.Parameters.AddWithValue("@author", author);
            cmd.Parameters.AddWithValue("@calories", calories);
            cmd.Parameters.AddWithValue("@preparingTime", preparingTime);
            cmd.Connection = con;

            cmd.ExecuteNonQuery();
        }

        public void insertUtensil(string utensilName, string dimention, int unit)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  insert into utensil
                    (utensilName, dimention, unit)
                    values
                    (@utensilName, @dimention, @unit);";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@utensilName", utensilName);
            cmd.Parameters.AddWithValue("@dimention", dimention);
            cmd.Parameters.AddWithValue("@unit", unit);
            cmd.Connection = con;

            cmd.ExecuteNonQuery();
        }

        public void insertIngredient(string ingredientName, string description)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  insert into ingredient
                    (ingredientName, description)
                    values
                    (@ingredientName, @description);";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@ingredientName", ingredientName);
            cmd.Parameters.AddWithValue("@description", description);
            cmd.Connection = con;

            cmd.ExecuteNonQuery();
        }

        public void insertCategory(string categoryName, string description)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  insert into category
                    (categoryName, description)
                    values
                    (@categoryName, @description);";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@categoryName", categoryName);
            cmd.Parameters.AddWithValue("@description", description);
            cmd.Connection = con;

            cmd.ExecuteNonQuery();
        }

        public void insertStep(int stepID, string description, string image)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  insert into step
                    (stepID, description, image)
                    values
                    (@stepID, @description, @image);";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@stepID", stepID);
            cmd.Parameters.AddWithValue("@description", description);
            cmd.Parameters.AddWithValue("@image", image);
            cmd.Connection = con;

            cmd.ExecuteNonQuery();
        }

        public void addStepToRecipie(string recipieName, int stepID, int id, int stepNum)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  insert into has
                    (recipieName, stepID, id, stepNum)
                    values
                    (@recipieName, @stepID, @id, @stepNum);";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@recipieName", recipieName);
            cmd.Parameters.AddWithValue("@stepID", stepID);
            cmd.Parameters.AddWithValue("@id", id);
            cmd.Parameters.AddWithValue("@stepNum", stepNum);
            cmd.Connection = con;

            cmd.ExecuteNonQuery();
        }

        public void addUtensilToStep(string utensilName, int stepID, int id)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  insert into usesUtensil
                    (utensilName, stepID, id)
                    values
                    (@utensilName, @stepID, @id);";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@utensilName", utensilName);
            cmd.Parameters.AddWithValue("@stepID", stepID);
            cmd.Parameters.AddWithValue("@id", id);
            cmd.Connection = con;

            cmd.ExecuteNonQuery();
        }

        public void addIngredientToStep(string ingredientName, int stepID, int id, int quantity, string unit)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  insert into usesIngredient
                    (ingredientName, stepID, id, quantity, unit)
                    values
                    (@ingredientName, @stepID, @id, @quantity, @unit);";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@ingredientName", ingredientName);
            cmd.Parameters.AddWithValue("@stepID", stepID);
            cmd.Parameters.AddWithValue("@id", id);
            cmd.Parameters.AddWithValue("@quantity", quantity);
            cmd.Parameters.AddWithValue("@unit", unit);
            cmd.Connection = con;

            cmd.ExecuteNonQuery();
        }

        public void addCategoryToStep(string recipieName, int categoryName)
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText =
                @"  insert into belongs
                    (recipieName, categoryName)
                    values
                    (@recipieName, categoryName);";
            cmd.Parameters.Clear();
            cmd.Parameters.AddWithValue("@recipieName", recipieName);
            cmd.Parameters.AddWithValue("@categoryName", categoryName);
            cmd.Connection = con;

            cmd.ExecuteNonQuery();
        }
    }
}
